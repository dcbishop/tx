-- Spawns a blue light
if not isInitilized(self) then
	local p = {}
	p['light_vmodel'] = VModel("cube.dae")
	p['light'] = Light(self.tag .. "_LIGHT", p['light_vmodel'])
	p['light'].isTempory = true
	p['light'].visible = false

	p['light'].x = 0.5
	p['light'].y = 0.5
	p['light'].z = 0.5
	p['light']:setDirectional(1.0)
	p['light'].ambient:setColour(0.0, 0.0, 0.0, 1.0)
	p['light'].diffuse:setColour(0.0, 0.0, 1.0, 1.0)
	p['light'].ca = 1.0
	p['light'].la = 0.0
	p['light'].qa = 0.0	

	self.area:addObject(p['light'])

	setProperties(self, p)
end
