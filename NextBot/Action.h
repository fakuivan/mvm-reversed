/* reverse engineering by sigsegv
 * based on TF2 version 20151002
 * NextBot: actions
 */


#define Continue() \
	return {   ActionTransition::CONTINUE,        nullptr,   nullptr }

#define ChangeTo(_nextaction, _reason) \
	return {  ActionTransition::CHANGE_TO,  (_nextaction), (_reason) }

#define SuspendFor(_nextaction, _reason) \
	return { ActionTransition::SUSPEND_FOR, (_nextaction), (_reason) }

#define Done(_reason) \
	return {        ActionTransition::DONE,       nullptr, (_reason) }


enum class ActionTransition : int
{
	CONTINUE    = 0,
	CHANGE_TO   = 1,
	SUSPEND_FOR = 2,
	DONE        = 3,
	CONTINUE2   = 4, // why? who knows
};


enum class ResultSeverity : int
{
	/* this is 100% guesswork */
	LOW      = 1,
	MEDIUM   = 2,
	CRITICAL = 3,
};


template<class T>
struct ActionResult
{
	ActionTransition transition;
	Action<T> *action;
	const char *reason;
};


template<class T>
struct EventDesiredResult : public ActionResult<T>
{
	ResultSeverity severity;
};


// most Action event handlers                          return { 0, nullptr, nullptr, 1 }
// CTFBotMvMDeployBomb::OnContact                      return { 4, nullptr, nullptr, 3 }
// CTFBotDeliverFlag::OnContact                        return { 2, new CTFBotMvMDeployBomb(), "Delivering the bomb!", 3 }
// CTFBotMoveToVantagePoint::OnMoveToSuccess           return { 3, nullptr, "Vantage point reached", 3 }
// CTFBotSpyHide::OnMoveToSuccess                      return { 0, nullptr, nullptr, 3 }
// CTFBotGetAmmo::OnMoveToFailure                      return { 3, nullptr, "Failed to reach ammo", 3 }
// CTFBotGetHealth::OnMoveToFailure                    return { 3, nullptr, "Failed to reach health kit", 3 }
// CTFBotSpyHide::OnMoveToFailure                      return { 0, nullptr, nullptr, 2 }
// CTFBotGetAmmo::OnStuck                              return { 3, nullptr, "Stuck trying to reach ammo", 3 }
// CTFBotGetHealth::OnStuck                            return { 3, nullptr, "Stuck trying to reach health kit", 3 }
// CTFBotSpySap::OnStuck                               return { 3, nullptr, "I'm stuck, probably on a sapped building that hasn't exploded yet", 3 }
// CEyeballBossStunned::OnInjured                      return { 4, nullptr, nullptr, 3 }
// CMerasmusBehavior::OnInjured                        return { 2, new CMerasmusDisguise(), "Disguise", 2 }
// CRobotBehavior::OnInjured                           return { 2, new CRobotEnterPanic(), "I've been attacked", 1 }
// CRobotEnterPanic::OnInjured                         return { 4, nullptr, "I'm entering panic and being attacked", 3 }
// CRobotLeavePanic::OnInjured                         return { 4, nullptr, "I'm leaving panic and being attacked", 3 }
// CRobotPanic::OnInjured                              return { 4, nullptr, "I'm panicking and getting attacked", 2 }
// CRobotSpawn::OnInjured                              return { 4, nullptr, "I'm spawning and being attacked", 3 }
// CTFBotPrepareStickybombTrap::OnInjured              return { 3, nullptr, "Ouch!", 2 }
// CTFBotSpyAttack::OnInjured                          return { 1, new CTFBotRetreatToCover(), "Time to get out of here!", 2 }
// CTFBotStickybombSentrygun::OnInjured                return { 3, nullptr, "Ouch!", 2 }
// CBotNPCArcherBehavior::OnKilled                     return { 3, nullptr, nullptr, 1 }
// CEyeballBossBehavior::OnKilled                      return { 1, new CEyeballBossDead(), "I died!", 3 }
// CZombieBehavior::OnKilled                           return { 3, nullptr, nullptr, 1 }
// CTFBotMainAction::OnOtherKilled                     return { 2, new CTFBotTaunt(), "Taunting our victim", 2 }
// CTFBotPushToCapturePoint::OnNavAreaChanged          return { 2, new CTFBotNavEntWait(), "Prerequisite commands me to wait", 2 }
// CTFBotPushToCapturePoint::OnNavAreaChanged          return { 2, new CTFBotNavEntMoveTo(), "Prerequisite commands me to move to an entity", 2 }
// CTFBotTacticalMonitor::OnNavAreaChanged             return { 2, new CTFBotNavEntWait(), "Prerequisite commands me to wait", 2 }
// CTFBotTacticalMonitor::OnNavAreaChanged             return { 2, new CTFBotNavEntMoveTo(), "Prerequisite commands me to move to an entity", 2 }
// CTFBotTacticalMonitor::OnCommandString              return { 2, new CTFGotoActionPoint(), "Received command to go to action point", 2 }
// CTFBotTacticalMonitor::OnCommandString              return { 2, new CTFBotEngineerBuilding(), "Building a Sentry at a hint location", 3 }
// CTFBotTacticalMonitor::OnCommandString              return { 2, new CTFTrainingAttackSentryActionPoint(), "Received command to attack sentry gun at next action point", 3 }
// CTFBotTacticalMonitor::OnCommandString              return { 2, new CTFBotTaunt(), "Received command to taunt", 1 }
// CTFBotTacticalMonitor::OnCommandString              return { 2, new CTFDespawn(), "Received command to go to de-spawn", 3 }
// CTFBotDefendPointBlockCapture::OnTerritoryContested return { 4, nullptr, nullptr, 1 }
// CTFBotDefendPointBlockCapture::OnTerritoryLost      return { 3, nullptr, "Lost the point", 3 }
// CTFBotPayloadBlock::OnTerritoryCaptured             return { 4, nullptr, nullptr, 2 }
// CTFBotPayloadBlock::OnTerritoryContested            return { 4, nullptr, nullptr, 2 }
// CTFBotPayloadBlock::OnTerritoryLost                 return { 4, nullptr, nullptr, 2 }
// CTFBotSeekAndDestroy::OnTerritoryCaptured           return { 3, nullptr, "Giving up due to point capture", 2 }
// CTFBotSeekAndDestroy::OnTerritoryContested          return { 3, nullptr, "Defending the point", 2 }
// CTFBotSeekAndDestroy::OnTerritoryLost               return { 3, nullptr, "Giving up due to point lost", 2 }


template<class T>
class Action : public INextBotEventResponder, public IContextualQuery
{
public:
	Action(/* TODO ??? */);
	virtual ~Action();
	
	/* INextBotEventResponder overrides */
	virtual INextBotEventResponder *FirstContainedResponder() const override final;
	virtual INextBotEventResponder *NextContainedResponder(INextBotEventResponder *prev) const override final;
	
	virtual void OnLeaveGround(CBaseEntity *ent) override final;
	virtual void OnLandOnGround(CBaseEntity *ent) override final;
	
	virtual void OnContact(CBaseEntity *ent, CGameTrace *trace) override final;
	
	virtual void OnMoveToSuccess(const Path *path) override final;
	virtual void OnMoveToFailure(const Path *path, MoveToFailureType fail) override final;
	
	virtual void OnStuck() override final;
	virtual void OnUnStuck() override final;
	
	virtual void OnPostureChanged() override final;
	virtual void OnAnimationActivityComplete(int i1) override final;
	virtual void OnAnimationActivityInterrupted(int i1) override final;
	virtual void OnAnimationEvent(animevent_t *a1) override final;
	
	virtual void OnIgnite() override final;
	virtual void OnInjured(const CTakeDamageInfo& info) override final;
	virtual void OnKilled(const CTakeDamageInfo& info) override final;
	virtual void OnOtherKilled(CBaseCombatCharacter *who, const CTakeDamageInfo& info) override final;
	
	virtual void OnSight(CBaseEntity *ent) override final;
	virtual void OnLostSight(CBaseEntity *ent) override final;
	
	virtual void OnSound(CBaseEntity *ent, const Vector& v1, KeyValues *kv) override final;
	virtual void OnSpokeConcept(CBaseCombatCharacter *who, const char *s1, AI_Response *response) override final;
	virtual void OnWeaponFired(CBaseCombatCharacter *who, CBaseCombatWeapon *weapon) override final;
	
	virtual void OnNavAreaChanged(CNavArea *area1, CNavArea *area2) override final;
	virtual void OnModelChanged() override final;
	virtual void OnPickUp(CBaseEntity *ent, CBaseCombatCharacter *who) override final;
	virtual void OnDrop(CBaseEntity *ent) override final;
	virtual void OnActorEmoted(CBaseCombatCharacter *who, int i1) override final;
	
	virtual void OnCommandAttack(CBaseEntity *ent) override final;
	virtual void OnCommandApproach(const Vector& v1, float f1) override final;
	virtual void OnCommandApproach(CBaseEntity *ent) override final;
	virtual void OnCommandRetreat(CBaseEntity *ent, float f1) override final;
	virtual void OnCommandPause(float f1) override final;
	virtual void OnCommandResume() override final;
	virtual void OnCommandString(const char *cmd) override final;
	
	virtual void OnShoved(CBaseEntity *ent) override final;
	virtual void OnBlinded(CBaseEntity *ent) override final;
	
	virtual void OnTerritoryContested(int i1) override final;
	virtual void OnTerritoryCaptured(int i1) override final;
	virtual void OnTerritoryLost(int i1) override final;
	
	virtual void OnWin() override final;
	virtual void OnLose() override final;
	
	
	virtual const char *GetName() const = 0;
	virtual bool IsNamed(const char *name) const;
	virtual char *GetFullName() const;
	
	virtual ActionResult<T> OnStart(T *actor, Action<T> *action);
	virtual ActionResult<T> Update(T *actor, float f1);
	virtual void OnEnd(T *actor, Action<T> *action);
	
	virtual ActionResult<T> OnSuspend(T *actor, Action<T> *action);
	virtual ActionResult<T> OnResume(T *actor, Action<T> *action);
	
	virtual Action<T> *InitialContainedAction(T *actor);
	
	virtual EventDesiredResult<T> OnLeaveGround(T *actor, CBaseEntity *ent);
	virtual EventDesiredResult<T> OnLandOnGround(T *actor, CBaseEntity *ent);
	
	virtual EventDesiredResult<T> OnContact(T *actor, CBaseEntity *ent, CGameTrace *trace);
	
	virtual EventDesiredResult<T> OnMoveToSuccess(T *actor, const Path *path);
	virtual EventDesiredResult<T> OnMoveToFailure(T *actor, const Path *path, MoveToFailureType fail);
	
	virtual EventDesiredResult<T> OnStuck(T *actor);
	virtual EventDesiredResult<T> OnUnStuck(T *actor);
	
	virtual EventDesiredResult<T> OnPostureChanged(T *actor);
	virtual EventDesiredResult<T> OnAnimationActivityComplete(T *actor, int i1);
	virtual EventDesiredResult<T> OnAnimationActivityInterrupted(T *actor, int i1);
	virtual EventDesiredResult<T> OnAnimationEvent(T *actor, animevent_t *a1);
	
	virtual EventDesiredResult<T> OnIgnite(T *actor);
	virtual EventDesiredResult<T> OnInjured(T *actor, const CTakeDamageInfo& info);
	virtual EventDesiredResult<T> OnKilled(T *actor, const CTakeDamageInfo& info);
	virtual EventDesiredResult<T> OnOtherKilled(T *actor, CBaseCombatCharacter *who, const CTakeDamageInfo& info);
	
	virtual EventDesiredResult<T> OnSight(T *actor, CBaseEntity *ent);
	virtual EventDesiredResult<T> OnLostSight(T *actor, CBaseEntity *ent);
	
	virtual EventDesiredResult<T> OnSound(T *actor, CBaseEntity *ent, const Vector& v1, KeyValues *kv);
	virtual EventDesiredResult<T> OnSpokeConcept(T *actor, CBaseCombatCharacter *who, const char *s1, AI_Response *response);
	virtual EventDesiredResult<T> OnWeaponFired(T *actor, CBaseCombatCharacter *who, CBaseCombatWeapon *weapon);
	
	virtual EventDesiredResult<T> OnNavAreaChanged(T *actor, CNavArea *area1, CNavArea *area2);
	virtual EventDesiredResult<T> OnModelChanged(T *actor);
	virtual EventDesiredResult<T> OnPickUp(T *actor, CBaseEntity *ent, CBaseCombatCharacter *who);
	virtual EventDesiredResult<T> OnDrop(T *actor, CBaseEntity *ent);
	virtual EventDesiredResult<T> OnActorEmoted(T *actor, CBaseCombatCharacter *who, int i1);
	
	virtual EventDesiredResult<T> OnCommandAttack(T *actor, CBaseEntity *ent);
	virtual EventDesiredResult<T> OnCommandApproach(T *actor, const Vector& v1, float f1);
	virtual EventDesiredResult<T> OnCommandApproach(T *actor, CBaseEntity *ent);
	virtual EventDesiredResult<T> OnCommandRetreat(T *actor, CBaseEntity *ent, float f1);
	virtual EventDesiredResult<T> OnCommandPause(T *actor, float f1);
	virtual EventDesiredResult<T> OnCommandResume(T *actor);
	virtual EventDesiredResult<T> OnCommandString(T *actor, const char *cmd);
	
	virtual EventDesiredResult<T> OnShoved(T *actor, CBaseEntity *ent);
	virtual EventDesiredResult<T> OnBlinded(T *actor, CBaseEntity *ent);
	
	virtual EventDesiredResult<T> OnTerritoryContested(T *actor, int i1);
	virtual EventDesiredResult<T> OnTerritoryCaptured(T *actor, int i1);
	virtual EventDesiredResult<T> OnTerritoryLost(T *actor, int i1);
	
	virtual EventDesiredResult<T> OnWin(T *actor);
	virtual EventDesiredResult<T> OnLose(T *actor);
	
	virtual bool IsAbleToBlockMovementOf(const INextBot *nextbot) const;
	
	
	void StorePendingEventResult(const EventDesiredResult<T>& result, const char *s1);
	Action<T> *ApplyResult(T *actor, Behavior<T> *behavior, ActionResult<T> result);
	
	ActionResult<T> InvokeOnStart(T *actor, Behavior<T> *behavior, Action<T> *action1, Action<T> *action2);
	ActionResult<T> InvokeUpdate(T *actor, Behavior<T> *behavior, float f1);
	void InvokeOnEnd(T *actor, Behavior<T> *behavior, Action<T> *action);
	
	ActionResult<T> InvokeOnResume(T *actor, Behavior<T> *behavior, Action<T> *action);
	Action<T> *InvokeOnSuspend(T *actor, Behavior<T> *behavior, Action<T> *action);
	
	char *BuildDecoratedName(char *s1, const Action<T> *action) const;
	char *DebugString() const;
	void PrintStateToConsole() const;
	
	
private:
	Behavior<T> *m_Behavior;        // +0x08
	Action<T> *m_ActionParent;      // +0x0c
	Action<T> *m_ActionChild;       // +0x10
	Action<T> *m_ActionWeSuspended; // +0x14
	Action<T> *m_ActionSuspendedUs; // +0x18
	T *m_Actor;                     // +0x1c
	EventDesiredResult<T> m_Result; // +0x20
	// +30 byte 0 (InvokeOnEnd only does stuff if set to TRUE)
	// +31 byte 0
};

template<> class Action<CBotNPCArcher>;
template<> class Action<CBotNPCDecoy>;
template<> class Action<CEyeballBoss>;
template<> class Action<CGhost>;
template<> class Action<CHeadlessHatman>;
template<> class Action<CMerasmus>;
template<> class Action<CSimpleBot>;
template<> class Action<CTFBot>;
template<> class Action<CTFRobotDestruction_Robot>;
template<> class Action<CZombie>;
