#include "qfu_xrulesub.h"

QString xrulesub(QString str, unsigned int x)
{
    if (str.contains("-X"))
    {
        QString num = "-";
        num.append(QString::number(x));

        QString newStr = str.replace("-X",num);


        return newStr;
    }
    else
        return str;
}
