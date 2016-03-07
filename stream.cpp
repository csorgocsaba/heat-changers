#include "stream.h"

Stream::Stream()
{
    numberofStreams++;
    this->number=numberofStreams;
}
int Stream::getNumber() const
{
    return number;
}

/*void Stream::setNumber(int value)
{
    number = value;
}*/
bool Stream::getType() const
{
    return type;
}

void Stream::setType(bool value)
{
    type = value;
}
double Stream::getTS() const
{
    return TS;
}

void Stream::setTS(double value)
{
    TS = value;
}
double Stream::getTT() const
{
    return TT;
}

void Stream::setTT(double value)
{
    TT = value;
}
double Stream::getATS() const
{
    return ATS;
}

void Stream::setATS()
{
    if(this->getType()){
        ATS = TS-deltaTmin/2;
    } else{
        ATS = TS+deltaTmin/2;
    }

}
double Stream::getATT() const
{
    return ATT;
}

void Stream::setATT()
{
    if(this->getType()){
        ATT = TT-deltaTmin/2;
    } else{
        ATT = TT+deltaTmin/2;
    }
}
double Stream::getDeltaTmin()
{
    return deltaTmin;
}

void Stream::setDeltaTmin(double value)
{
    deltaTmin = value;
}

double Stream::getHCF() const
{
    return HCF;
}

void Stream::setHCF(double value)
{
    HCF = value;
}


int Stream::numberofStreams=0;
double Stream::deltaTmin;

