import { createContext } from "svelte";

export const [getDisableAnimation, setDisableAnimation] = createContext<() => boolean>();