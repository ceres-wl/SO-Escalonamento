// We dont want it to be truly random, there is probably a better solution to this, but wtever
let SEED = 1;
export function resetSeed(){ SEED = 1 }

export function randomHexColor(maxCombinedBrightness = 256*3, maxSingleComponent = 256){
    const randomComponent = () => {
        const comp = Math.floor(seededRandom(SEED++)*Math.min(maxSingleComponent, maxCombinedBrightness));
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
    .map(value => ({ value, sort: seededRandom(SEED++) }))
    .sort((a, b) => a.sort - b.sort)
    .map(({ value }) => value);

    return "#" + components
    .map((comp) => {
        const str = comp.toString(16);
        return str.length==1?"0"+str:str;
    })
    .join("");
}

export function hashedHexColor(str: string){
    const CUR_SEED = SEED;
    SEED = generateHash(str);
    const color = randomHexColor();
    SEED = CUR_SEED;
    return color;
}

// from https://stackoverflow.com/a/7616484
function generateHash(str: string) {
    let hash = 0;
    for (const char of str) {
        hash = (hash << 5) - hash + char.charCodeAt(0);
        hash |= 0; // Constrain to 32bit integer
    }
    return hash;
};

// from https://stackoverflow.com/a/19303725
// works for us because being truly random doesnt matter at all
function seededRandom(seed: number) {
    var x = Math.sin(seed++) * 10000;
    return x - Math.floor(x);
}