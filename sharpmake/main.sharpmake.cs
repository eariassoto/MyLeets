// Copyright (c) 2021 Emmanuel Arias
using Sharpmake;
using System.IO;

[module: Sharpmake.Include("common.sharpmake.cs")]

[module: Sharpmake.Include("../exercises/test/test.application.sharpmake.cs")]


namespace MyLeets
{
    [Sharpmake.Generate]
    class MyLeetsSolution : BaseSolution
    {
        public MyLeetsSolution()
        {
            Name = "MyLeets";
            AddTargets(new Target(
                Platform.win32 | Platform.win64,
                DevEnv.vs2019,
                Optimization.Debug | Optimization.Release
            ));
        }

        public override void ConfigureAll(Configuration conf, Target target)
        {
            base.ConfigureAll(conf, target);
            conf.AddProject<test_Exercise>(target);

        }
    }
}


public static class Globals
{
    // branch root path relative to current sharpmake file location
    public const string RelativeRootPath = @"../";
    public static string RootDirectory;
    public static string SharpmakeDirectory { get { return Path.Combine(RootDirectory, "sharpmake"); } }
}

public static class main
{
    private static void ConfigureRootDirectory()
    {
        FileInfo fileInfo = Util.GetCurrentSharpmakeFileInfo();
        string rootDirectory = Path.Combine(fileInfo.DirectoryName, Globals.RelativeRootPath);
        Globals.RootDirectory = Util.SimplifyPath(rootDirectory);
    }

    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments arguments)
    {
        ConfigureRootDirectory();

        arguments.Generate<MyLeets.MyLeetsSolution>();
    }
}
