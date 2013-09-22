#ifndef GRAPHIC_ENGINE_H_
#define GRAPHIC_ENGINE_H_

class GraphicEngine {
public:
	static GraphicEngine* instance() {
		static GraphicEngine GraphicEngine_;
		return &GraphicEngine_;
	};
	void RenderFrame();
private:
	GraphicEngine() {};
	~GraphicEngine() {};
	void DrawObstacles();
	void DrawBullets();
	void DrawSpaceShip();
};

#define Graphic GraphicEngine::instance()

#endif /* GRAPHIC_ENGINE_H_ */
