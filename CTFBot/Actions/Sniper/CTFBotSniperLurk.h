/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * CTFBot actions: sniper: lurk
 * used in MvM: TODO
 */


class CTFBotSniperLurk : public Action<CTFBot>
{
public:
	CTFBotSniperLurk(/* TODO */);
	virtual ~CTFBotSniperLurk();
	
	virtual const char *GetName() const override;
	
	virtual ActionResult<CTFBot> OnStart(CTFBot *actor, Action<CTFBot> *action) override;
	virtual ActionResult<CTFBot> Update(CTFBot *actor, float f1) override;
	virtual void OnEnd(CTFBot *actor, Action<CTFBot> *action) override;
	
	virtual ActionResult<CTFBot> OnSuspend(CTFBot *actor, Action<CTFBot> *action) override;
	virtual ActionResult<CTFBot> OnResume(CTFBot *actor, Action<CTFBot> *action) override;
	
	virtual QueryResponse ShouldRetreat(const INextBot *nextbot) const override;
	virtual QueryResponse ShouldAttack(const INextBot *nextbot, const CKnownEntity *threat) const override;
	virtual const CKnownEntity *SelectMoreDangerousThreat(const INextBot *nextbot, const CBaseCombatCharacter *them, const CKnownEntity *threat1, const CKnownEntity *threat2) const override;
	
	UNKNOWN FindHint(CTFBot *actor);
	UNKNOWN FindNewHome(CTFBot *actor);
	
private:
	// TODO
};
