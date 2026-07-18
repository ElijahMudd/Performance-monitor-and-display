using System.Diagnostics;
using System.IO.Ports;
using System.Runtime.InteropServices;
using System.Threading;
using System.Management;

string portName = args.Length > 0 ? args[0] : "COM5";
SerialPort port = new(portName, 9600);

port.Open();

if (OperatingSystem.IsWindows())
{

PerformanceCounter cpu = new PerformanceCounter(
    "Processor",
    "% Processor Time",
    "_Total"
);

PerformanceCounter ram = new PerformanceCounter(
    "Memory",
    "% Committed Bytes In Use"
);

while (true)
{
    Thread.Sleep(1000);

    float cpuUsage = cpu.NextValue();
    float ramUsage = ram.NextValue();

    port.WriteLine($"CPU: {MathF.Floor(cpuUsage)}%|RAM: {ramUsage:0}%");
}

} else 
{
    port.WriteLine("Os not supported");
}