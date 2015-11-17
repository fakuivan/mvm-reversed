/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * Pathfinding: path follower
 */


class PathFollower : public Path
{
public:
	PathFollower();
	virtual ~PathFollower();
	
	virtual const Segment *GetCurrentGoal() const override;
	
	virtual void Invalidate() override;
	
	virtual void Draw(const Segment *seg) const override;
	
	virtual void OnPathChanged(INextBot *nextbot, ResultType rtype) override;
	
	virtual void Update(INextBot *nextbot);
	virtual void SetMinLookAheadDistance(float f1);
	virtual CBaseEntity *GetHindrance() const;
	virtual bool IsDiscontinuityAhead(INextBot *nextbot, SegmentType stype, float f1) const;
	
	void AdjustSpeed(INextBot *nextbot);
	Vector Avoid(INextBot *nextbot, const Vector& v1, const Vector& v2, const Vector& v3);
	bool CheckProgress(INextBot *nextbot);
	bool Climbing(INextBot *nextbot, const Segment *seg, const Vector& v1, const Vector& v2, float f1);
	CBaseEntity *FindBlocker(INextBOt *nextbot);
	bool IsAtGoal(INextBot *nextbot) const;
	bool JumpOverGaps(INextBOt *nextbot, const Segment *seg, const Vector& v1, const Vector& v2, float f1);
	bool LadderUpdate(INextBot *nextbot);
	
protected:
	// 4450 
	// ...
	// 4754 dword 0, Segment* returned by GetCurrentGoal
	// 4758 float -1.0f, set by SetMinLookAheadDistance
	// 4760 CountdownTimer
	// 476c CountdownTimer
	// 4778 CHandle<CBaseEntity>, referenced by GetHindrance
	// 477c byte 0
	// 4780 
	// ...
	// 47d0 float 25.0f
};

class CTFPathFollower : public PathFollower
{
	// TODO
	// TODO: struct and vtable in IDA
};