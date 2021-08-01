using Sharpmake;

[module: Sharpmake.Include("../../sharpmake/common.sharpmake.cs")]
[module: Sharpmake.Include("../../external/spdlog.library.sharpmake.cs")]

[Generate]
class CommonLibLibrary : CXXStaticLibraryProject
{
    public CommonLibLibrary()
    {
        Name = "common_lib";

        AddTargets(
            new Target(
                Platform.win32 | Platform.win64,
                DevEnv.vs2019,
                Optimization.Debug | Optimization.Release
            )
        );
    }

    public override void ConfigureAll(Project.Configuration conf, Target target)
    {
        base.ConfigureAll(conf, target);

        conf.AddPublicDependency<External_SpdLogLibrary>(target);
    }
}
