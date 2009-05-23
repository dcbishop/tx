-- Spawns a "Cube" object that can be pushed around
if not isInitilized(self) then
	local p = {}

	local size = 0.45

	p['vmodel'] = VModel("cube.dae")
	p['object'] = RigidBody("Cube", p['vmodel'])
	local object = p['object']

	p['object'].isTempory = true
	p['object'].location = self.location
	p['spawntime'] = time
	setProperties(self, p)
else
	local p = getProperties(self)

	if not p['spawned'] then
		-- We spawn the Cube on a delay due to the physics engine shooting it randomly around if done at start
		if time > p['spawntime'] + 1500 then
			self.isVisible = false
			local size = 0.125
			p['shape'] = p['object']:loadShapeBox(size, size, size)
			p['object']:setShape(p['shape'])
			p['object']:setMass(0.1)
			p['object'].location = self.location
			p['spawned'] = true
		end
	end
end
