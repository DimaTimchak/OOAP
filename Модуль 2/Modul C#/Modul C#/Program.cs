using System;

public interface IAlarmCImpl
{
    void Ring();
    void Notify();
}

public class AlarmCImplSimple : IAlarmCImpl
{
    public void Ring()
    {
        Console.WriteLine("The sound of a simple alarm clock!");
    }

    public void Notify()
    {
        Console.WriteLine("Message: The alarm clock has started its work!");
    }
}

public abstract class AlarmC
{
    protected IAlarmCImpl impl;

    public AlarmC(IAlarmCImpl impl)
    {
        this.impl = impl;
    }

    public abstract void Start();
    public abstract void Stop();
    public abstract void ToWake();
}

public class SimpleAlarmC : AlarmC
{
    public SimpleAlarmC(IAlarmCImpl impl) : base(impl) { }

    public override void Start()
    {
        Console.WriteLine("The alarm goes off...");
    }

    public override void Stop()
    {
        Console.WriteLine("The alarm is stopped.");
    }

    public override void ToWake()
    {
        impl.Ring();
        impl.Notify();
    }S
}

class Program
{
    static void Main()
    {
        IAlarmCImpl alarmImpl = new AlarmCImplSimple();

        AlarmC alarm = new SimpleAlarmC(alarmImpl);

        alarm.Start();
        alarm.ToWake();
        alarm.Stop();
    }
}
