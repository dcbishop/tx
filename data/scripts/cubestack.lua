-- Spawn a stack of cubes
cubestacksize = 10

if not isInitilized(self) then
	local p = {}

	local size = 0.125
	local current_size = size

	p['vmodel'] = VModel("cube.dae")

	for cube = 0, cubestacksize do
		p['object'..cube] = RigidBody("Cube"..cube, p['vmodel'])
		p['object'..cube].isTempory = true
		p['object'..cube].location = self.location
		p['object'..cube].y = p['object'..cube].y + current_size
		current_size = current_size + (2*size) + 0.01
	end

	p['spawntime'] = time
	setProperties(self, p)
else
	local p = getProperties(self)

	if not p['spawned'] then
		-- We spawn the cubes on a delay due to the physics engine shooting it randomly around if done at start
		if time > p['spawntime'] + 1500 then
			self.isVisible = false
			local size = 0.125
			for cube = 0, cubestacksize do
				p['shape'] = p['object'..cube]:loadShapeBox(size, size, size)
				p['object'..cube]:setShape(p['shape'])
				p['object'..cube]:setMass(0.1)
				p['object'..cube].location = self.location
				p['spawned'] = true
			end
		end
	end
end
