/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * CTFBot actions: scenario payload: block
 * used in MvM: TODO
 */


class CTFBotPayloadBlock : public Action<CTFBot>
{
public:
	CTFBotPayloadBlock(/* TODO */);
	virtual ~CTFBotPayloadBlock();
	
	virtual const char *GetName() const override;
	
	virtual ActionResult<CTFBot> OnStart(CTFBot *actor, Action<CTFBot> *action) override;
	virtual ActionResult<CTFBot> Update(CTFBot *actor, float f1) override;
	
	virtual ActionResult<CTFBot> OnResume(CTFBot *actor, Action<CTFBot> *action) override;
	
	virtual EventDesiredResult<CTFBot> OnMoveToSuccess(CTFBot *actor, const Path *path) override;
	virtual EventDesiredResult<CTFBot> OnMoveToFailure(CTFBot *actor, const Path *path, MoveToFailureType fail) override;
	
	virtual EventDesiredResult<CTFBot> OnStuck(CTFBot *actor) override;
	
	virtual EventDesiredResult<CTFBot> OnTerritoryContested(CTFBot *actor, int i1) override;
	virtual EventDesiredResult<CTFBot> OnTerritoryCaptured(CTFBot *actor, int i1) override;
	virtual EventDesiredResult<CTFBot> OnTerritoryLost(CTFBot *actor, int i1) override;
	
	virtual QueryResponse ShouldHurry(const INextBot *nextbot) const override;
	virtual QueryResponse ShouldRetreat(const INextBot *nextbot) const override;
	
private:
	// TODO
};
