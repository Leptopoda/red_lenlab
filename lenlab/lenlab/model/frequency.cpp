#include "frequency.h"

namespace model {

Frequency::Frequency(QObject *parent) : Component(parent)
{

}

QString
Frequency::getNameNominative()
{
    return "ie Frequenzanalyse";
}

QString
Frequency::getNameAccusative()
{
    return "ie Frequenzanalyse";
}

} // namespace model
