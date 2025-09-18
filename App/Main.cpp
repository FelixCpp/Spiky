#include <memory>
#include <format>

import Spiky;

struct SpikesGame : Spiky::Sketch
{
	bool Setup() override
	{
		return true;
	}

	void Event(const Spiky::WindowEvent& event) override
	{
		event.Visit(
			[](const Spiky::WindowEvent::Closed&)
			{
				Spiky::Info("Window close event received");
			},
			[](const Spiky::WindowEvent::Resized& resized)
			{
				Spiky::Info(std::format("Window has been resized: {}, {}", resized.Width, resized.Height));
			},
			[](const auto&)
			{
				Spiky::Info("An unknown event has been received");
			}
		);
	}

	void Draw() override
	{
		Spiky::Background(40, 50, 220);
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
