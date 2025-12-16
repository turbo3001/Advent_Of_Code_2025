//
// Created by Luke on 14/12/2025.
//

#pragma once

struct Globals {
	bool VerboseMode : 1 = false;
	bool Part2Mode : 1 = false;

	static Globals& Get() {
		static Globals instance;
		return instance;
	}

	Globals() {}

	Globals(Globals const&) = delete;
	void operator=(Globals const&) = delete;
};
