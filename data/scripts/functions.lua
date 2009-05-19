function getTimeDiff()
	return (self.last_update - time) / 1000
end

function getObjectByTag(tag)
	return gm:getObjectByTag(tag)
end

function getAreaByTag(tag)
	return gm:getAreaByTag(tag)
end

function getCreatureByTag(tag)
	return gm:getCreatureByTag(tag)
end

function getPlayer()
	return gm:getCreatureByTag("Player")
end

function isInitilized(object)
	if getProperties(object) then
		return true
	else
		return false
	end
end

function setProperties(object, properties)
	globals[object:getMemoryAddress()] = properties
end

function getProperties(ob)
	local properties = globals[ob:getMemoryAddress()]
	if not properties then
		--properties = {}
		--setProperties(object, properties)
	end
	return properties
end

function getAreaProperties(area)
	local properties = getProperties(area)
	if not properties then
		properties = {}
		setProperties(area, properties)
	end
	return properties
end


-- TODO: These functions are no longer needed here

-- Gets the distance to the object from self
function getDistanceTo(object)
	diff_x = object.x - self.x
	diff_z = object.z - self.z
	return math.sqrt(math.pow(diff_x, 2) + math.pow(diff_z, 2))
end

function getDirectionTo(object) 
	diff_x = object.x - self.x
	diff_z = object.z - self.z
	return math.atan2(diff_z, diff_x)
end

function hello()
	print("Hello")
end
