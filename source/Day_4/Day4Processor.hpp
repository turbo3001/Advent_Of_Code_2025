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
	typedef std::vector<bool> MapRow;

	struct PaperMap{
		std::vector<MapRow> rows;

		bool GetPos(const int x, const int y) const {
			return rows[y][x];
		}

		void Print() const {
			for (const MapRow& Row : rows) {
				for (const bool& Column : Row) {
					std::cout << (Column ? "@" : ".");
				}
				std::cout << std::endl;
			}
		}
	} Map;

	intmax_t ProcessRow(MapRow& NewRow) const;

	int CurrentY = 0;
	bool Finished = false;
};
