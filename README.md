[![Github All Releases](https://img.shields.io/github/downloads/turbosmurfen/vlcsay/total.svg)
# VLCSay - VLC Now Playing for mIRC  

![VLCSay on mIRC 7.76](https://github.com/turbosmurfen/VLCSay/blob/main/img/vlcsay.png)

VLCSay running on mIRC

# Requirements

* **Supported Operating System**: Windows Vista, 7, 8.1, 10 and 11.
* **Visual C++ Redistributable 2015-2022 (x86)**  
* **Tested mIRC version**: 7.76
* **HDD/SSD Space**: 17,5 KB.  

# Installation 

1. Download `vlcsay_vx.x.x.zip` zip archive of VLCSay in Assets in the [Releases](https://github.com/turbosmurfen/VLCSay/releases/latest) section.
2. If you don't have `Visual C++ Redistributable 2015-2022 (x86)` installed, download from here: [https://aka.ms/vs/17/release/vc_redist.x86.exe](https://aka.ms/vs/17/release/vc_redist.x86.exe).  
3. Right Click on the archive which is named _vlcsay_vx.x.x.zip_, extract the archive.  
   * Optional - verify the hash: 
       1. Open up powershell and **cd** to **vlcsay_vx.x.x** folder. 
       2. Run this command `Get-FileHash vlcsay.dll`. 
       3. Then look if the sha256 checksum is correct from [Releases](https://github.com/turbosmurfen/VLCSay/releases/latest). 
       4. If it's correct you should be fine. 
4. Open mIRC.
5. Paste `//noop $sfile($mircdir)` to mIRC and press enter. You will see a file picker dialog.
6. Copy `vlcsay.dll` and paste inside this popup window. **OR** save it where you have your other DLL files. 

# Usage

Use: _$dll(pathtovlcsay\vlcsay.dll,**command**,)_

| Command       | output        | Description   |   
| --- | --- | --- |  
| version       | x.x.x         | Will output which version of VLCSay you use.  |  
| creator       | x - Made by   | Will output the creator of VLCSay.  |  
| status        | 0             | VLC is not running. |
| status        | 1             | VLC is not playing a song. |
| status        | 2             | VLC is playing a song.
| song          | artist - title | Will output artist and title. |

### Controlling VLCSay from mIRC

Use: _/dll pathtovlcsay\vlcsay.dll control **command**_

| Command       |Description   |
| --- | --- | 
| playpause | Plays or Pause the track. |
| play | Plays the track. |
| pause | Pauses the track. |
| stop | Stops the playing track. |
| next | Play next track. |
| previous | Play previous track. |

### Send current song to chat

Please ensure VLCSay alias **vnp** is not triggered by any other scripts.  
  
To add the script:
1. In mIRC, click on **Scripts Editor** or **ALT** + **R**
2. Select Remote.
3. Click on File > New.  
4. Copy the code below and paste inside the new Script file
5. Save. Now you can use `/vnp` in any channel or private messages.

```mirc
alias vnp {
  var %status $dll(vlcsay.dll,status,)
  if (%status == 1) echo -a VLC is not playing a song.
  elseif (%status == 2) say VLC » $dll(vlcsay.dll,song,)
  else echo -a VLC is not running.
}
```

# Frequently Asked Questions

> **Q**: I can't find vx.x.x on download section, what do I do wrong?
> 
> **A**: **x.x.x** stands for the version number, look for that in releases.

> **Q**: How does VLCSay work?
>
> **A**: It works by reading Windows API calls from VLC to detect _artist - title_, plus using VLC's media controls.

> **Q**: Does VLCSay requires internet connection?
>
> **A**: No. VLCSay does work offline.  

> **Q**: I am getting an error: _$dll: unable to open 'C:\Users\USERNAME\AppData\Roaming\mIRC\pathtovlcsay\vlcsay.dll_
>
> **A**: This can show up for 2 reasons:  
> 
> 1. You have put the DLL file in the wrong location.
> 2. You need to install [Visual C++ Redistributable 2015-2022 (x86)](https://aka.ms/vs/17/release/vc_redist.x86.exe)  

## Credits

I have learned more about making mIRC reading and writing for DLL-file from [Wikichip](https://en.wikichip.org/wiki/mirc/dynamic-link_library)    
