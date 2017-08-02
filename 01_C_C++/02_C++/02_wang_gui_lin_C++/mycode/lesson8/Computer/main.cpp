#include <iostream>

using namespace std;
/*中间接口*/
class Cpu{
public:
    virtual void run()=0;
};
class Mem{
public:
    virtual void run()=0;
};
class Disk{
public:
    virtual void run()=0;
};
/*底层细节*/
class IntelCpu:public Cpu{
public:
    virtual void run(){
        cout<<"I'm Intel Cpu, I have sixteen core, 3.4gh."<<endl;
    }
};
class KingStonMem:public Mem
{
    public:
    void run(){
        cout<<"My memory is Kingston,16g 1333"<<endl;
    }
};
class WestDataDisk:public Disk
{
    public:
    void run(){
        cout<<"My Disk is western data, I am solid, "
              "I have the capacity 100G"<<endl;
    }
};

class AMDCpu:public Cpu{
public:
    virtual void run(){
        cout<<"I'm Amd Cpu, I have eight core, 3.4gh."<<endl;
    }
};
class HuaiWeiMem:public Mem
{
    public:
    void run(){
        cout<<"My memory is HuaWei,8g 1333"<<endl;
    }
};
class SeagateDisk:public Disk
{
    public:
    void run(){
        cout<<"My Disk is Seagate, I am solid, "
              "I have the capacity 0.5T"<<endl;
    }
};
/*上层调用*/
class Computer{
public:
    Computer(Cpu * pc, Mem * pm, Disk * pd)
        :_pc(pc),_pm(pm),_pd(pd){}
    void work(){
        _pc->run();
        _pm->run();
        _pd->run();
    }
    ~Computer(){
        delete _pc;
        delete _pm;
        delete _pd;
    }
private:
    Cpu * _pc;
    Mem * _pm;
    Disk * _pd;
};
int main()
{
    Computer c(new IntelCpu, new KingStonMem, new WestDataDisk);
    c.work();
    cout<<"---------------------------------------------------------------"<<endl;
    Computer c2(new AMDCpu, new HuaiWeiMem, new SeagateDisk);
    c2.work();
    return 0;
}

