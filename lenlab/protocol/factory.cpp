#include "factory.h"

#include "usb/exception.h"

#include "lenlab_version.h"

#include <QDebug>

namespace protocol {

Factory::Factory(QObject *parent) : QObject(parent)
{
    connect(&mTimer, &QTimer::timeout,
            this, &Factory::on_timeout);

    mTimer.setSingleShot(true);
}

void
Factory::connectToBoard(int boottime)
{
    Q_ASSERT(!mBoard);

    try {
        auto device = mBus.query(LENLAB_VID, LENLAB_PID);
        if (device) {
            mBoard.reset(new Board(device));
            // nothing shall throw after mBoard is set
            // else catch starts the timer
            connect(mBoard.data(), &Board::error,
                    this, &Factory::on_board_error);
            emit log("Lenlab-Board gefunden.");
            // wait for the board to boot, it just got power
            QTimer::singleShot(boottime, this, &Factory::on_found);
        }
        else {
            mTimer.start(500);
        }
    } catch (const usb::Exception & e) {
        emit error(e.getMsg());
        mTimer.start(3000);
    }
}

void
Factory::on_timeout()
{
    connectToBoard(mBootTime);
}

void
Factory::on_board_error(QString const & msg)
{
    mBoard.clear();
    emit error(msg);
}

void
Factory::on_task_error(pTask const & task)
{
    mBoard.clear();
    emit error(task->getErrorMessage());
}

void
Factory::on_found()
{
    pMessage cmd(new Message());
    cmd->setCommand(::init);
    auto init = mBoard->startTask(cmd);
    connect(init.data(), &Task::succeeded,
            this, &Factory::on_init);
    connect(init.data(), &Task::failed,
            this, &Factory::on_task_error);
}

void
Factory::on_init(pTask const & task)
{
    Q_UNUSED(task);

    pMessage cmd(new Message());
    cmd->setCommand(::getName);
    auto name = mBoard->startTask(cmd);
    connect(name.data(), &Task::succeeded,
            this, &Factory::on_name);
    connect(name.data(), &Task::failed,
            this, &Factory::on_task_error);
}

void
Factory::on_name(pTask const & task)
{
    Q_UNUSED(task);

    pMessage cmd(new Message());
    cmd->setCommand(::getVersion);
    auto version = mBoard->startTask(cmd);
    connect(version.data(), &Task::succeeded,
            this, &Factory::on_version);
    connect(version.data(), &Task::failed,
            this, &Factory::on_task_error);
}

void
Factory::on_version(pTask const & task)
{
    auto reply = task->getReply();
    auto length = reply->getUInt32BufferLength();
    if (length == 3 || length == 2) {
        auto array = reply->getUInt32Buffer();

        auto major = array[0];
        auto minor = array[1];

        if (major == MAJOR && minor == MINOR) {
            mBoard->setVersion(major, minor);
            disconnect(mBoard.data(), &Board::error,
                       this, &Factory::on_board_error);
            auto board = mBoard;
            mBoard.clear();
            emit ready(board);
        }
        else {
            auto msg = QString("Ungültige Version %1.%2. Lenlab erwartet mindestens %3.%4.").arg(major).arg(minor).arg(MAJOR).arg(MINOR);
            mBoard.clear();
            emit error(msg);
        }
    }
    else {
        auto msg = QString("Das Lenlab-Board antwortet mit einer ungültigen Version.");
        mBoard.clear();
        emit error(msg);
    }
}

} // namespace protocol
