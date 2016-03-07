#ifndef STREAM_H
#define STREAM_H

class Stream
{
public:

    Stream();
    double getTS() const;
    void setTS(double value);
    double getTT() const;
    void setTT(double value);

    int getNumber() const;
//    void setNumber(int value);

    bool getType() const;
    void setType(bool value);

    double getATS() const;
    void setATS();

    double getATT() const;
    void setATT();


    static int numberofStreams;
    static double deltaTmin;

    double getHCF() const;
    void setHCF(double value);

    static double getDeltaTmin();
    static void setDeltaTmin(double value);

private:


    int number;
    bool type; //if Hot it is true, if Cold it is false
    double TS;
    double TT;
    double HCF;
    double ATS; //adjusted Supply Temerature
    double ATT; //adjusted Target Temperature
};

#endif // STREAM_H
