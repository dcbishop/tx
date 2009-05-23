-- An automatic door that open when the player approaches.
height = 1.0
if not isInitilized(self) then
	local properties = {}

	properties['doormodel'] = VModel("door.dae")	
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
	closeObj.y = closeObj.y + (height/2.0)

	local openTag = self.tag .. "_OPEN"
	local openObj = Object(openTag, properties['ptrvmodel'])
	openObj.isTempory = true
	openObj.isVisible = false
	openObj.location = self.location
	openObj.y = closeObj.y + height * (3/2)

	--local area = self.area
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
		if time > properties['spawntime'] + 1500 then
			self.isVisible = false
			local size = 0.5
			local location = self.location
			location.y = location.y + size * 2

			properties['shape'] = properties['doorObj']:loadShapeBox(0.5, 0.5, 0.05)
			properties['doorObj']:setShape(properties['shape'])
			properties['doorObj']:setKinematic()
			properties['doorObj'].location = location
			properties['doorObj']:setRotation(self.rotation)
			properties['spawned'] = true
		end
	else
		
		--properties['doorObj'].ry = 1.0
		--properties['doorObj'].ry = 1.0
		--properties['doorObj'].angle = properties['doorObj'].angle + 1
		--properties['doorObj'].location = self.location
		
		--properties['doorObj'].rotation = self.rotation
		--properties['doorObj'].angle = 90
		--print(properties['doorObj'].angle)
		
		--properties['doorObj'].rotation = self.rotation
	end



	local door = properties['doorObj']
	if properties['switches'] then
		local pa = getAreaProperties(door.area)

		if pa['active_switches'] >= pa['num_switches'] then
			properties['locked'] = false
		else
			properties['locked'] = true
		end
	end

	local closeObj = properties['closeObj']
	local player = getPlayer()
	if player and closeObj:getDistanceTo(player) < 1.0 then
		if properties['locked'] == false then
			properties['currentObj'] = properties['openObj']
		end
	else
		properties['currentObj'] = properties['closeObj']
	end

	local currentObj = properties['currentObj']
	local speed = 0.01
	local ds = speed * getTimeDiff()

	if door:getDistanceTo(currentObj) > speed then

		if door.y < currentObj.y then
			door.y = door.y + speed
		elseif door.y > currentObj.y then
			door.y = door.y - speed
		end
		
	end
end
