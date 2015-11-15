/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * CTFBot actions: medic: heal
 * used in MvM: TODO
 */


class CTFBotMedicHeal : public Action<CTFBot>
{
public:
	CTFBotMedicHeal(/* TODO */);
	virtual ~CTFBotMedicHeal();
	
	virtual const char *GetName() const override;
	
	virtual ActionResult<CTFBot> OnStart(CTFBot *actor, Action<CTFBot> *action) override;
	virtual ActionResult<CTFBot> Update(CTFBot *actor, float f1) override;
	
	virtual ActionResult<CTFBot> OnResume(CTFBot *actor, Action<CTFBot> *action) override;
	
	virtual EventDesiredResult<CTFBot> OnMoveToSuccess(CTFBot *actor, const Path *path) override;
	virtual EventDesiredResult<CTFBot> OnMoveToFailure(CTFBot *actor, const Path *path, MoveToFailureType fail) override;
	
	virtual EventDesiredResult<CTFBot> OnStuck(CTFBot *actor) override;
	
	virtual EventDesiredResult<CTFBot> OnActorEmoted(CTFBot *actor, CBaseCombatCharacter *who, int i1) override;
	
	virtual QueryResponse ShouldHurry(const INextBot *nextbot) const override;
	virtual QueryResponse ShouldRetreat(const INextBot *nextbot) const override;
	virtual QueryResponse ShouldAttack(const INextBot *nextbot, const CKnownEntity *threat) const override;
	virtual QueryResponse IsHindrance(const INextBot *nextbot, CBaseEntity *it) const override;
	
	UNKNOWN ComputeFollowPosition(CTFBot *actor);
	UNKNOWN IsGoodUberTarget(CTFPlayer *player) const;
	UNKNOWN IsReadyToDeployUber(const CWeaponMedigun *medigun) const;
	UNKNOWN IsStable(CTFPlayer *player) const;
	UNKNOWN IsVisibleToEnemy(CTFBot *actor, const Vector& v1) const;
	UNKNOWN SelectPatient(CTFBot *actor, CTFPlayer *player);
	
private:
	// TODO
};
