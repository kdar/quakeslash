using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

// Code developed by InfernoDevelopment.com

namespace Log
{
  public class Logger
  {
    public static void log(String message)
    {
      DateTime datet = DateTime.Now;
      String filePath = "Log" + datet.ToString("MM_dd") + ".log";
      if (!File.Exists(filePath))
      {
        FileStream files = File.Create(filePath);
        files.Close();
      }
      try
      {
        StreamWriter sw = File.AppendText(filePath);
        sw.WriteLine(datet.ToString("MM/dd hh:mm") + "> " + message);
        sw.Flush();
        sw.Close();
      }
      catch (Exception e)
      {
        Console.WriteLine(e.Message.ToString());
      }
    }
  }
}