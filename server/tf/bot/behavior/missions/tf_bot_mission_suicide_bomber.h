/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * server/tf/bot/behavior/missions/tf_bot_mission_suicide_bomber.h
 * used in MvM: TODO
 */


// sizeof: 0x4850
class CTFBotMissionSuicideBomber : public Action<CTFBot>
{
public:
	CTFBotMissionSuicideBomber();
	virtual ~CTFBotMissionSuicideBomber();
	
	virtual const char *GetName() const override;
	
	virtual ActionResult<CTFBot> OnStart(CTFBot *actor, Action<CTFBot> *action) override;
	virtual ActionResult<CTFBot> Update(CTFBot *actor, float f1) override;
	virtual void OnEnd(CTFBot *actor, Action<CTFBot> *action) override;
	
	virtual EventDesiredResult<CTFBot> OnStuck(CTFBot *actor) override;
	
	virtual EventDesiredResult<CTFBot> OnKilled(CTFBot *actor, const CTakeDamageInfo& info) override;
	
	virtual QueryResponse ShouldAttack(const INextBot *nextbot, const CKnownEntity *threat) const override;
	
private:
	void StartDetonate(CTFBot *actor, bool reached_goal, bool killed);
	void Detonate(CTFBot *actor);
	
	// 0x0034 CHandle<CBaseEntity>
	// 0x0038 Vector
	PathFollower m_PathFollower; // +0x0044
	CountdownTimer m_ctTimer1;   // +0x4818
	CountdownTimer m_ctTimer2;   // +0x4824
	CountdownTimer m_ctTimer3;   // +0x4830
	// 0x483c byte "is detonating"
	// - w OnStart =0
	// - w Detonate =1
	// - r OnStuck (if false, then call StartDetonate)
	// - r OnKilled (if false, then call StartDetonate)
	// 0x483d byte "detonated because reached goal"
	// - w OnStart =0
	// - w StartDetonate =b1
	// - r Detonate (if false, speak TLK_MVM_SENTRY_BUSTER_DOWN)
	// - r Update (if true, fire event "mvm_sentrybuster_detonate", give achievement 2326 "Ctrl + Assault + Delete: Destroy a sentry buster before it reaches its target.")
	// 0x483e byte "detonated because killed"
	// - w OnStart =0
	// - w StartDetonate =b2
	// - r Detonate (if true, fire event "mvm_sentrybuster_killed")
	// - r Detonate (if true, increment CPopulationManager::GetCurrentWave()->field_34)
	// 0x4840 ???
	// 0x4844 ???
	// 0x4848 ???
	// 0x484c ???
};
