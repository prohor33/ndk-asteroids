#ifndef GRAPHIC_ENGINE_H_
#define GRAPHIC_ENGINE_H_

#include "main.h"
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
	void drawObj(shared_ptr<SpaceObject> obj);
};

#define Graphic GraphicEngine::instance()

#endif /* GRAPHIC_ENGINE_H_ */
