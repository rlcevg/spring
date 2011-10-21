/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef QTPFS_PATH_HDR
#define QTPFS_PATH_HDR

#include <vector>

#include "System/float3.h"

namespace QTPFS {
	struct IPath {
		IPath(): id(0), ownerID(-1U), pointIdx(0), radius(0.0f), synced(true) {}
		virtual ~IPath() {}

		unsigned int GetID() const { return id; }
		void SetID(unsigned int id) { this->id = id; }

		void SetOwnerID(unsigned int ownerID) { this->ownerID = ownerID; }
		void SetPointIdx(unsigned int pointIdx) { this->pointIdx = pointIdx; }
		void SetRadius(float radius) { this->radius = radius; }
		void SetSynced(bool synced) { this->synced = synced; }

		unsigned int GetOwnerID() const { return ownerID; }
		unsigned int GetPointIdx() const { return pointIdx; }
		float GetRadius() const { return radius; }
		bool GetSynced() const { return synced; }

		virtual void SetEndPoints(const float3&, const float3&) {}
		virtual void SetPoint(unsigned int, const float3&) {}
		virtual const float3& GetPoint(unsigned int) const { return ZeroVector; }

		virtual const float3& GetSourcePoint() const { return ZeroVector; }
		virtual const float3& GetTargetPoint() const { return ZeroVector; }

		virtual unsigned int NumPoints() const { return 0; }
		virtual void AllocPoints(unsigned int) {}

	protected:
		unsigned int id;
		unsigned int ownerID;
		unsigned int pointIdx;

		float radius;
		bool synced;
	};

	struct Path: public IPath {
	public:
		Path(): IPath() {}
		Path(const Path& p) { *this = p; }
		Path& operator = (const Path& p) {
			id = p.GetID();
			ownerID = p.GetOwnerID();
			pointIdx = p.GetPointIdx();
			synced = p.GetSynced();
			radius = p.GetRadius();
			points = p.GetPoints();
			return *this;
		}
		~Path() { points.clear(); }

		void SetEndPoints(const float3& sp, const float3& tp) {
			points.push_back(sp);
			points.push_back(tp);
		}
		void SetPoint(unsigned int i, const float3& p) { points[std::min(i, NumPoints() - 1)] = p; }
		const float3& GetPoint(unsigned int i) const { return points[std::min(i, NumPoints() - 1)]; }

		const float3& GetSourcePoint() const { return points[                0]; }
		const float3& GetTargetPoint() const { return points[points.size() - 1]; }

		unsigned int NumPoints() const { return (points.size()); }
		void AllocPoints(unsigned int n) {
			points.clear();
			points.resize(n);
		}
		const std::vector<float3>& GetPoints() const { return points; }

	private:
		std::vector<float3> points;
	};
};

#endif

