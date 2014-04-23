using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;

using Extemory;
using System.Reflection;
using System.IO;

namespace QuakeSlash
{
  [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Unicode), Serializable]
  struct RunData
  {
    [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 2048)]
    public string executepath;
  }

  /// <summary>
  /// Interaction logic for MainWindow.xaml
  /// </summary>
  public partial class MainWindow : Window
  {
    List<Extemory.Injection.InjectedModule> injectedModules = new List<Extemory.Injection.InjectedModule>();

    //[DllImport("PokerSlash.InjectHelper.dll", CallingConvention = CallingConvention.Cdecl)]
    //public static extern int Inject(int processId);

    //[DllImport("PokerSlash.InjectHelper.dll", CallingConvention = CallingConvention.Cdecl)]
    //public static extern void Call(String func/*, IntPtr[] args*/);

    public MainWindow()
    {
      InitializeComponent();
    }

    private void button1_Click(object sender, RoutedEventArgs e)
    {
      //Thread clientThread = new Thread(new ParameterizedThreadStart((obj) => {
      //  Process[] processes = Process.GetProcessesByName("Lobby");
      //  Inject(processes[0].Id);
      //}));
      //clientThread.IsBackground = true;
      //clientThread.Start(null);

      try
      {
        //Log.Logger.log("Process.GetProcessesByName");
        List<Process> procs = new List<Process>(Process.GetProcessesByName("plugin-container"));
        procs.AddRange(Process.GetProcessesByName("quakeliveoffline"));
        foreach (var proc in procs)
        {
          //Log.Logger.log("proc.InjectLibrary");
          Extemory.Injection.InjectedModule injectedModule = proc.InjectLibrary(@"QuakeSlash.Hook.dll");
          injectedModules.Add(injectedModule);
          RunData data;
          //Log.Logger.log("Directory.GetCurrentDirectory");
          data.executepath = Directory.GetCurrentDirectory();

          //Log.Logger.log("new Thread");
          Thread clientThread = new Thread(new ParameterizedThreadStart((obj) =>
          {
            // returnwindows after Stop() is called on the hook
            //Log.Logger.log("module.CallExport");
            var result = injectedModule.CallExport<RunData>("Run", data);
            injectedModule.Eject();
          }));
          clientThread.IsBackground = true;
          //Log.Logger.log("thread.Start");
          clientThread.Start(null);
        }
      }
      catch (Exception exc)
      {
        MessageBox.Show(exc.ToString());
      }
    }

    private void button2_Click(object sender, RoutedEventArgs e)
    {
      //Thread clientThread = new Thread(new ParameterizedThreadStart((obj) =>
      //{
      //  Call("Stop"/*, new IntPtr[]{}*/);
      //}));
      //clientThread.IsBackground = true;
      //clientThread.Start(null);
      foreach (var module in injectedModules)
      {
        try
        {
          module.CallExport("Stop");
        }
        catch (Exception exc)
        {

        }
      }
    }
  }
}
