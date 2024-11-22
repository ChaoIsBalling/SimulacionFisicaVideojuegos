#include "AnchoredSpringFG.h"
AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos):SpringForceGenerator(k, resting, nullptr)
{
	other = new Particula(anchor_pos, { 0,0,0 }, { 0,0,0 }, 100,1000);

	render= new RenderItem(CreateShape(PxBoxGeometry(1,1,1)), &PxTransform(anchor_pos), {1.0,0,0,1});
}
AnchoredSpringFG::~AnchoredSpringFG()
{
DeregisterRenderItem(render);
delete other;
}
