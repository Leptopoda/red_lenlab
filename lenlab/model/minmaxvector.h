/*

Lenlab, an oscilloscope software for the TI LaunchPad EK-TM4C123GXL
Copyright (C) 2017 Christoph Simon and the Lenlab developer team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef MINMAXVECTOR_H
#define MINMAXVECTOR_H

#include <QVector>

namespace model {

class MinMaxVector : public QVector<double>
{
public:
    void append(double value);

    void clear();

    double getMin();
    double getMax();

private:
    typedef QVector<double> super;

    double min = 0;
    double max = 0;
};

} // namespace model

#endif // MINMAXVECTOR_H
