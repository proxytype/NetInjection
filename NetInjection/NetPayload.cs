using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace NetInjection
{
    class NetPayload
    {
        static int showInjection(String caller)
        {
            while (true)
            {
                Console.WriteLine("HI FROM INJECTION");
                Thread.Sleep(1000);
            }

            return 1;
        }
    }
}
