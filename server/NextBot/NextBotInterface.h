/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * server/NextBot/NextBotInterface.h
 */


class INextBot : public INextBotEventResponder
{
public:
	enum NextBotDebugType : unsigned int
	{
		BEHAVIOR   = (1 << 0), // NextBotBehavior
		LOOK_AT    = (1 << 1), // NextBotBodyInterface
		PATH       = (1 << 2), // NextBotPath, NextBotPathFollow, NextBotChasePath
		ANIMATION  = (1 << 3),
		LOCOMOTION = (1 << 4), // NextBotLocomotionInterface
		VISION     = (1 << 5), // NextBotVisionInterface
		HEARING    = (1 << 6),
		EVENTS     = (1 << 7), // NextBotEventResponderInterface
		ERRORS     = (1 << 8),
	};
	
	struct NextBotDebugLineType
	{
		NextBotDebugType type; // +0x000
		char buf[0x100];       // +0x004
	};
	
	INextBot();
	virtual ~INextBot();
	
	virtual INextBotEventResponder *FirstContainedResponder() const override;
	virtual INextBotEventResponder *NextContainedResponder(INextBotEventResponder *prev) const override;
	
	virtual void Reset();
	virtual void Update();
	virtual void Upkeep();
	
	virtual bool IsRemovedOnReset() const;
	
	virtual CBaseEntity *GetEntity() const = 0;
	virtual NextBotCombatCharacter *GetNextBotCombatCharacter() const;
	
	virtual ILocomotion *GetLocomotionInterface() const;
	virtual IBody *GetBodyInterface() const;
	virtual IIntention *GetIntentionInterface() const;
	virtual IVision *GetVisionInterface() const;
	
	virtual bool SetPosition(const Vector& pos);
	virtual Vector& GetPosition() const;
	
	virtual bool IsEnemy(const CBaseEntity *ent) const;
	virtual bool IsFriend(const CBaseEntity *ent) const;
	virtual bool IsSelf(const CBaseEntity *ent) const;
	
	virtual bool IsAbleToClimbOnto(const CBaseEntity *ent) const;
	virtual bool IsAbleToBreak(const CBaseEntity *ent) const;
	virtual bool IsAbleToBlockMovementOf(const INextBot *nextbot) const;
	
	virtual bool ShouldTouch(const CBaseEntity *ent) const;
	
	virtual bool IsImmobile() const;
	virtual float GetImmobileDuration() const;
	virtual void ClearImmobileStatus();
	virtual float GetImmobileSpeedThreshold() const;
	
	virtual PathFollower *GetCurrentPath() const;
	virtual void SetCurrentPath(const PathFollower *follower);
	virtual void NotifyPathDestruction(const PathFollower *follower);
	
	virtual bool IsRangeLessThan(CBaseEntity *ent, float dist) const;
	virtual bool IsRangeLessThan(const Vector& vec, float dist) const;
	virtual bool IsRangeGreaterThan(CBaseEntity *ent, float dist) const;
	virtual bool IsRangeGreaterThan(const Vector& vec, float dist) const;
	
	virtual float GetRangeTo(CBaseEntity *ent) const;
	virtual float GetRangeTo(const Vector& vec) const;
	virtual float GetRangeSquaredTo(CBaseEntity *ent) const;
	virtual float GetRangeSquaredTo(const Vector& vec) const;
	
	virtual bool IsDebugging(unsigned int type) const;
	virtual char *GetDebugIdentifier() const;
	virtual bool IsDebugFilterMatch(const char *filter) const;
	virtual void DisplayDebugText(const char *text) const;
	
	bool BeginUpdate();
	void EndUpdate();
	
	void DebugConColorMessage(NextBotDebugType type, const Color& color, const char *fmt, ...);
	
	void GetDebugHistory(unsigned int mask, CUtlVector<const NextBotDebugLineType *> *dst) const;
	void ResetDebugHistory();
	
	void RegisterComponent(INextBotComponent *component);
	
protected:
	void UpdateImmobileStatus();
	
	INextBotComponent *m_ComponentList; // +0x04
	PathFollower *m_CurrentPath;        // +0x08
	// 0c int, default -1, from NextBotManager::Register
	// 10 byte
	// 14 dword -999
	// 18 
	int m_iDebugTextOffset;             // +0x1c
	Vector m_vecLastPosition;           // +0x20
	CountdownTimer m_ctImmobileCheck;   // +0x2c
	IntervalTimer m_itImmobileEpoch;    // +0x38
	ILocomotion *m_LocoInterface;       // +0x3c
	IBody *m_BodyInterface;             // +0x40
	IIntention *m_IntentionInterface;   // +0x44
	IVision *m_VisionInterface;         // +0x48
	// 4c CUtlVector<NextBotDebugLineType *>
};
