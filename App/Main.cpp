#include <memory>

import Spiky;

struct SpikesGame : Spiky::Sketch
{
	bool Setup() override
	{
		Spiky::SetWindowSize(100, 100, true);
		Spiky::SetWindowSize(300, 600, true);
		Spiky::SetWindowSize(400, 500, true);
		Spiky::SetWindowSize(200, 300, true);
		return true;
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
