#include <memory>

import Spiky;

struct SpikesGame : Spiky::Sketch
{
	bool Setup() override
	{
		Spiky::SetWindowSize(100, 100, true);

		return true;
	}

	void Event(const Spiky::WindowEvent& event) override
	{
		
	}

	void Draw() override
	{
		
	}

	void Destroy() override
	{
		
	}
};

int main() {
	return Spiky::Launch([]
	{
		return std::make_unique<SpikesGame>();
	});
}
