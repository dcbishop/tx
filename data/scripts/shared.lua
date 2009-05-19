-- This is a basic script for storing area properties that are accessed across scripts
if not isInitilized(self) then
	local properties = {}
	self.isVisible = false

	if not isInitilized(self.area) then
		setProperties(self.area)
	end

	setProperties(self, {})
end
