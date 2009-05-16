-- Makes the object run away from the player.
player = getPlayer()
if player then
	-- Get the distance to the player
	distance = getDistanceTo(player)

	-- If we are to close to the player
	if distance < 2.0 then
		-- Find the direction to the player
		direction = getDirectionTo(player)
	
		dt = getTimeDiff()

		-- Face away from player
		self.angle = math.deg(-direction)-90.0
		
		self.x = self.x + math.cos(direction) * 1.0 * dt
		self.z = self.z + math.sin(direction) * 1.0 * dt
		--print("Run away!")
	end
end

