<script setup lang="ts">
import { ref, computed } from 'vue'
// api definition
interface ChilApi {
  doChili(
    text: string,
    accept: (result: boolean) => void,
    reject: (msg: string) => void,
  ): void;
}
const chilApi = window as unknown as ChilApi;
function doChili(text: string): Promise<boolean> {
  return new Promise<boolean>((accept, reject) => chilApi.doChili(text, accept, reject))
}
// reactive data
const powerLevel = ref<number|null>(null)
const inProgress = ref(false)
// computed data
const powerLevelNorm = computed(() => powerLevel.value ?? 0)
// functions
async function quest(text: string): Promise<void> {
  powerLevel.value = await doChili(text) ? <number>powerLevel.value + 1 : <number>powerLevel.value
}
async function doit() {
  inProgress.value = true
  powerLevel.value = 0
  try {
    await quest("Do you often find it hard to read or predict what other people are thinking or feeling?")
    await quest("Do changes to your daily routine or environment frequently cause you significant distress?")
    await quest("Do you prefer to focus deeply on specific interests or topics, sometimes to the exclusion of other activities?")
    await quest("Do you find making or maintaining eye contact uncomfortable or avoid it whenever possible?")
    await quest("Do you often take things very literally and have difficulty understanding figures of speech, jokes, or sarcasm?")
  }
  catch {
    powerLevel.value = null
  }
  finally {
    inProgress.value = false
  }
}
</script>

<template>
  <v-app>
    <v-main>
      <v-container width="1024">
        <h2 class="mb-2 ml-4">Take the Test</h2>
        <v-card title="Power Level">
          <div class="ma-5">
            <v-progress-linear
              v-model="powerLevelNorm"
              color="blue-darken-3"
              :indeterminate="powerLevel === null"
              :stream="inProgress"
              rounded
              max="5"
              height="20"
            ></v-progress-linear>
          </div>
        </v-card>
        <div class="d-flex justify-center mt-3">
          <v-btn color="purple" @click="doit" size="x-large">JUST DO IT</v-btn>
        </div>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped>
</style>
