/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * server/tf/bot/behavior/engineer/tf_bot_engineer_build_teleport_entrance.h
 * used in MvM: TODO
 */


// sizeof: 0x4808
class CTFBotEngineerBuildTeleportEntrance : public Action<CTFBot>
{
public:
	CTFBotEngineerBuildTeleportEntrance(/* TODO */);
	virtual ~CTFBotEngineerBuildTeleportEntrance();
	
	virtual const char *GetName() const override;
	
	virtual ActionResult<CTFBot> OnStart(CTFBot *actor, Action<CTFBot> *action) override;
	virtual ActionResult<CTFBot> Update(CTFBot *actor, float f1) override;
	
	virtual EventDesiredResult<CTFBot> OnStuck(CTFBot *actor) override;
	
private:
	// TODO
};