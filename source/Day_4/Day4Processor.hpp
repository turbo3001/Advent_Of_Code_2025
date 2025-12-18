//
// Created by Luke on 17/12/2025.
//

#pragma once
#include "../Common/IDayProcessor.h"


class Day4Processor : public IDayProcessor
{
public:
	explicit  Day4Processor(const std::string& InputFileName);
	bool IsFinished() const override;
	intmax_t Step(const intmax_t lastValue) override;
	void ReproduceInputFile() override;

private:
	struct MapRow{
		std::vector<bool> columns;
	};

	struct {
		std::vector<MapRow> rows;

		bool GetPos(const int x, const int y) const {
			return rows[y].columns[x];
		}
	} PaperMap;

	int CurrentY = 0;
};
