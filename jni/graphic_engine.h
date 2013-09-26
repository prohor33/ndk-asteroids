#ifndef GRAPHIC_ENGINE_H_
#define GRAPHIC_ENGINE_H_

class SpaceObject;

class GraphicEngine {
public:
	static GraphicEngine* instance() {
		static GraphicEngine GraphicEngine_;
		return &GraphicEngine_;
	};
	void renderFrame();
private:
	GraphicEngine() {};
	~GraphicEngine() {};
	void drawObj(SpaceObject* obj);
};

#define Graphic GraphicEngine::instance()

#endif /* GRAPHIC_ENGINE_H_ */
