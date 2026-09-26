export function randomHexColor(maxCombinedBrightness = 256*3, maxSingleComponent = 256){
    const randomComponent = () => {
        const comp = Math.floor(Math.random()*Math.min(maxSingleComponent, maxCombinedBrightness));
        maxCombinedBrightness -= comp;
        return comp;
    }
    
    let components = new Array(3)
    .fill(undefined)
    .map(randomComponent);

    // Shuffle, from https://stackoverflow.com/questions/2450954/how-to-randomize-shuffle-a-javascript-array
    // We shuffle the components to avoid the bias introduced by the maxCombinedBrightness method we are using,
    // without this, colors would be biased towards red
    components = components
    .map(value => ({ value, sort: Math.random() }))
    .sort((a, b) => a.sort - b.sort)
    .map(({ value }) => value);

    return "#" + components
    .map((comp) => {
        const str = comp.toString(16);
        return str.length==1?"0"+str:str;
    })
    .join("");
}