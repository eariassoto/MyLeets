using Sharpmake;

[module: Sharpmake.Include("../../sharpmake/common.sharpmake.cs")]
[module: Sharpmake.Include("../common_lib/common_lib.library.sharpmake.cs")]

[Generate]
class cci_2_1_delete_duplicates_Exercise : BaseProject
{
    public cci_2_1_delete_duplicates_Exercise()
    {
        Name = "cci_2_1_delete_duplicates";

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

        conf.AddPublicDependency<CommonLibLibrary>(target);
    }
}
