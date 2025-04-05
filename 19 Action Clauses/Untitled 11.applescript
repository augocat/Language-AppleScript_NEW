tell application "TextEdit"
	activate
	repeat
		try
			with timeout of 5 seconds
				display dialog ("Quick, type a word:") Â
					default answer "" giving up after 5
			end timeout
			if text returned of result is "" then
				display alert "You cheated! 'Bye."
				exit repeat
			end if
		on error number error_number
			if error_number is -128 then exit repeat
			delay 1
			beep
			display alert ("You weren't quick enough!") Â
				message ("Respond in 5 seconds. Try again!")
		end try
	end repeat
end tell
