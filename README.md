
## Dependences

- [ofxJSON](https://github.com/jefftimesten/ofxJSON)
- [ofxFTGL](https://github.com/Flightphase/ofxFTGL)

## Install

Install dependences: 

```
	cd openFrameworks/addons
	git clone --depth 1 http://github.com/jefftimesten/ofxJSON.git
	git clone --depth 1 http://github.com/Flightphase/ofxFTGL.git
```

## Add to project

Install ```ofxTangramTile``` to your project using the ProjectGenerator, dragging folder or Adam’s [OFPlugin](https://github.com/admsyn/OFPlugin). 

On the project Properties (the blue icons with the name of your project) go to `Building Settings` > `Linking` > `Other Linker Flags` and add `-lcurl`

