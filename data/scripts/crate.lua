-- Spawns a "Create" object that can be pushed around
if not isInitilized(self) then
	local p = {}

	local size = 0.45

	p['vmodel'] = VModel("LargeMetalCrate.dae")
	p['object'] = RigidBody("Crate", p['vmodel'])
	local object = p['object']

	p['object'].isTempory = true
	--self.area:addObject(p['object'])
	--p['shape'] = p['object']:loadShapeBox(size, size, size)

	--p['object']:setShape(p['shape'])
	--p['object']:disableRotation()

	local location = self.location
	location.y = location.y + size
	p['object'].location = location
	p['spawntime'] = time
	setProperties(self, p)
else
	local p = getProperties(self)

	if not p['spawned'] then
		-- We spawn the crate on a delay due to the physics engine shooting it randomly around if done at start
		if time > p['spawntime'] + 500 then
			self.isVisible = false
			local size = 0.45
			local location = self.location
			location.y = location.y + size
			--p['object'].location = location
			p['shape'] = p['object']:loadShapeBox(size, size, size)
			p['object']:setShape(p['shape'])
			p['object']:disableRotation()
			p['spawned'] = true
		end
	end
end
