This is a fork of the original GTA V FoV modification by DrDaxxy. Now the mod is loaded by Script Hook V.

All credit goes to DrDaxxy for the mod, and Jitnaught for converting for use with Script Hook V.

Here is a modified version of the original readme:

This mod allows you to freely set your desired fields of view (first-person walking, driving, aiming, ADS, crouching, and third-person) in Grand Theft Auto V.

Tested and working on the worldwide Steam and retail/Rockstar Warehouse version as of October 11, 2016 - there's no guarantee a future patch won't break it, but this mod will be updated for compatibility if necessary.

Be advised: We do not yet know the game's anti-cheating measures - use at your own risk. This mod modifies game memory and as such looks like a cheat, and may even be considered one in online multiplayer as having a higher field of view can put players at a competitive advantage. I consider it about as risky as SweetFX, so not very, but a risk is still there.

The latest version (non-Script Hook V) can always be found at https://github.com/drdaxxy/gta5fov/releases

The latest version (Script HookV) can always be found at https://github.com/Jitnaught/gta5fov/releases

-------

Installation instructions:

- Install Script Hook V.
- Find your GTA V installation folder (e.g. C:\Program Files (x86)\Steam\SteamApps\common\Grand Theft Auto V). It should have files such as GTAV.exe and bink2w64.dll in it.
- Extract fov.ini and GTA5FoV.asi into that folder.
- Install the Visual C++ 2015(!) x64 runtime using the provided vcredist_x64.exe file if you haven't already.
- Change the contents of fov.ini to your desired vertical(!) fields of view (ADS is aiming down sight). If you only know the horizontal FoV you want, here's a handy calculator: http://www.rjdown.co.uk/projects/bfbc2/fovcalculator.php
- All done! Launch the game as usual.

-------

Anticipated questions / known issues:

Q: I don't see any "dll".
A: Windows doesn't display known file extensions by default - if you just see a "bink2w64" file, that's okay, that's what I meant.

Q: Does this work on the Rockstar Warehouse version of the game too?
A: Yes.

Q: The game refuses to launch when I have the mod installed.
A: Did you install vcredist_x64.exe? The version (2015) is important! Microsoft names all their 64-bit packages, regardless of version, vcredist_x64.exe, so you may have installed one such file before which was older, so you'll still need to install this one.
!!! THIS WAS UPDATED SINCE THE LAST FOV MOD RELEASE !!!

Q: Okay, but I don't trust you to run a file from you as Administrator.
A: The official download is available at https://www.microsoft.com/en-US/download/details.aspx?id=48145

Q: Why doesn't the FoV slider in the camera menu work anymore?
A: The mod overrides it. If you want the default values back, you can uninstall it. If you want an ingame way of changing field of view, I might try utilising the cheat code prompt for that, but no guarantees.

Q: So how do I uninstall this?
A: Just delete GTA5FoV.asi and fov.ini from your GTA V installation folder again.

Q: I don't want the mod to change all fields of view, how do I disable only some changes?
A: Edit the fov.ini file and comment out the line (add a ; in front of it).

Q: I set the FoV to 100 and everything looks weird!
A: You need to convert your FoV to the vertical FoV, see the calculator linked above.

Q: Where's the (non-Script Hook V) source code?
A: https://github.com/drdaxxy/gta5fov

Q: Where's the (Script Hook V) source code?
A: https://github.com/Jitnaught/gta5fov

Q: Where do I get the latest (non-Script Hook V) version?
A: https://github.com/drdaxxy/gta5fov/releases

Q: Where do I get the latest (Script Hook V) version?
A: https://github.com/Jitnaught/gta5fov/releases

Q: My question wasn't answered / where can I discuss this?
A: The Reddit post: http://www.reddit.com/r/GrandTheftAutoV_PC/comments/32n8m0/i_made_a_mod_for_freely_setting_your_firstperson/ or preferably the issue tracker on GitHub.

-------

Changelog

1.33 (October 11, 2016)
- (internal) Update MSVC version (because I don't have 2013 installed anymore).
***This means you need the 2015 redistributable now.***
- Update signatures, fix mod for latest patch (fixes #13)

1.32 (December 17, 2015)
- Update signatures, fix mod for latest patch (fixes #10)

1.31 (June 12, 2015)
- Update signatures, fix mod for latest patch (fixes #6)

1.3 (April 18, 2015)
- Support disabling individual FoV mods by commenting out
- Support chain-loading other dsound.dll wrappers
- Disable third-person FoV mod by default (some people are reporting issues)

1.2 (April 18, 2015)
- Polished and released source
- Switched to INI for configuration
- Added aiming, driving, crouching, ADS and third-person settings

1.11 (April 15, 2015)
- Bundled vcredist_x64.exe

1.1 (April 15, 2015)
- Added debug log output.
- Changed wrapped DLL to dsound.dll for compatibility with non-Steam version.

1.0 (April 15, 2015)
- Initial release
