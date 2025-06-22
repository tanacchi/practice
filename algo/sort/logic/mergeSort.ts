import type { SortAlgorithm } from "./types";

export const mergeSort: SortAlgorithm<number> = (arr: number[]): number[] => {
	if (arr.length <= 1) {
		return arr;
	}
	const mid = Math.floor(arr.length / 2);
	const left = mergeSort(arr.slice(0, mid));
	const right = mergeSort(arr.slice(mid));
	return merge(left, right);
};

const merge = <T>(sortedList1: T[], sortedList2: T[]): T[] => {
	const result: T[] = [];
	let i = 0;
	let j = 0;
	while (i < sortedList1.length && j < sortedList2.length) {
		if (sortedList1[i] < sortedList2[j]) {
			result.push(sortedList1[i]);
			i++;
		} else {
			result.push(sortedList2[j]);
			j++;
		}
	}
	result.push(...sortedList1.slice(i++));
	result.push(...sortedList2.slice(j++));
	return result;
};
