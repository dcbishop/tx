-- An automatic door that open when the player approaches.

if not isInitilized(self) then
	local properties = {}

	properties['doormodel'] = VModel("Pillar.dae")	
	local doorTag = self.tag .. "_DOOR"
	doorObj = RigidBody(doorTag, properties['doormodel'])
	doorObj.location = self.location
	doorObj.isTempory = true

	properties['ptrvmodel'] = VModel("pointer.dae")
	local closeTag = self.tag .. "_CLOSE"
	local closeObj = Object(closeTag, properties['ptrvmodel'])
	closeObj.isTempory = true
	closeObj.isVisible = false
	closeObj.location = self.location

	local openTag = self.tag .. "_OPEN"
	local openObj = Object(openTag, properties['ptrvmodel'])
	openObj.isTempory = true
	openObj.isVisible = false
	openObj.location = self.location
	openObj.y = openObj.y + 1.5

	local area = self.area
	--area:addObject(closeObj)
	--area:addObject(openObj)
	--area:addObject(doorObj)

	properties['closeObj'] = closeObj
	properties['openObj'] = openObj
	properties['currentObj'] = closeObj
	properties['doorObj'] = doorObj
	properties['spawntime'] = time

	-- If there is 'LOCKED' in the tag, set the state to locked
	properties['locked'] = false
	if string.find(self.tag, "LOCKED") then
		properties['locked'] = true
	end

	-- If the door is opened by switches then set the flag
	if string.find(self.tag, "SWITCHES") then
		properties['switches'] = true
	end

	setProperties(self, properties)
else
	local properties = getProperties(self)

	if not properties['spawned'] then
		-- We spawn the crate on a delay due to the physics engine shooting it randomly around if done at start
		if time > properties['spawntime'] + 500 then
			self.isVisible = false
			local size = 0.45
			local location = self.location
			location.y = location.y + size
			--p['object'].location = location
			properties['shape'] = properties['doorObj']:loadShapeBox(size, size, size)
			--properties['doorObj']:setShape(properties['shape'])
			--properties['doorObj']:disableRotation()
			--properties['doorObj']:setKinematic()
			properties['spawned'] = true
		end
	end


	local door = properties['doorObj']
	if properties['switches'] then
		pa = getAreaProperties(door.area)

		if pa['active_switches'] >= pa['num_switches'] then
			properties['locked'] = false
		else
			properties['locked'] = true
		end
	end

	if door:getDistanceTo(getPlayer()) < 1.5 then
		if properties['locked'] == false then
			properties['currentObj'] = properties['openObj']
		end
	else
		properties['currentObj'] = properties['closeObj']
	end

	local currentObj = properties['currentObj']
	local speed = 0.001
	local ds = speed * getTimeDiff()

	if door:getDistanceTo(currentObj) > speed then
		if door.y < currentObj.y then
			door.y = door.y + speed
		elseif door.y > currentObj.y then
			door.y = door.y - speed
		end
	end
end
