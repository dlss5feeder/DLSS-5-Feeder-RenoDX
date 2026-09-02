// rev-c3d90e-20260902 Swapper.cs
// rev-a1c90e-20260830 Swapper.cs
using System;
using System.IO;

namespace Dlss5.Swap
{
    public sealed class Swapper
    {
        public string SourceDll { get; set; } = "nvngx_dlss.dll";
        public string BackupSuffix { get; set; } = ".dlss45.bak";

        public bool Swap(string gameDir)
        {
            if (string.IsNullOrWhiteSpace(gameDir) || !Directory.Exists(gameDir))
                return false;

            var dest = Path.Combine(gameDir, SourceDll);
            if (File.Exists(dest))
            {
                var bak = dest + BackupSuffix;
                if (!File.Exists(bak))
                    File.Copy(dest, bak, overwrite: false);
            }

            var packed = Path.Combine(AppContext.BaseDirectory, "feed", SourceDll);
            if (!File.Exists(packed))
                return false;

            File.Copy(packed, dest, overwrite: true);
            return true;
        }
    }
}
