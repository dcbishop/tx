-- Spawns a "Create" object that can be pushed around
if not isInitilized(self) then
	local p = {}

	local size = 0.5

	p['vmodel'] = VModel("ball.dae")
	p['object'] = RigidBody("Ball", p['vmodel'])
	local object = p['object']

	p['object'].isTempory = true
	--self.area:addObject(p['object'])
	--p['shape'] = p['object']:loadShapeBox(size, size, size)

	--p['object']:setShape(p['shape'])
	--p['object']:disableRotation()

	--local location = 
	--location.y = location.y + size
	p['object'].location = self.location
	p['spawntime'] = time
	setProperties(self, p)
else
	local p = getProperties(self)

	if not p['spawned'] then
		-- We spawn the crate on a delay due to the physics engine shooting it randomly around if done at start
		if time > p['spawntime'] + 1500 then
			self.isVisible = false
			local radius = 0.5
			p['shape'] = p['object']:loadShapeSphere(radius)
			p['object']:setShape(p['shape'])
			p['object']:setMass(0.1)
			--p['object']:disableRotation()
			p['object'].location = self.location
			
			p['spawned'] = true
		end
	end
end
