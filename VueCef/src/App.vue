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
const animal = ref<string|null>(null)
const inProgress = ref(false)
// computed data
const resultText = computed(() => {
  if (inProgress.value) {
    return "Test in progress..."
  }
  else if (animal.value === null) {
    return "NO DATA"
  }
  else {
    return `You are a: ${animal.value}`
  }
})
// functions
async function doit() {
  inProgress.value = true;
  animal.value = null;

  try {
    if (await doChili("Do you primarily live in water?")) {
      if (await doChili("Do you breathe underwater with gills?")) {
        if (await doChili("Are you a saltwater species?")) {
          if (await doChili("Are you found near coral reefs?")) {
            animal.value = "Clownfish";
          } else {
            animal.value = "Great White Shark";
          }
        } else {
          if (await doChili("Do you migrate upstream to spawn?")) {
            animal.value = "Salmon";
          } else {
            animal.value = "Trout";
          }
        }
      } else {
        if (await doChili("Are you warm-blooded?")) {
          if (await doChili("Do you live and travel in pods?")) {
            animal.value = "Dolphin";
          } else {
            animal.value = "Manatee";
          }
        } else {
          if (await doChili("Do you typically hop to get around?")) {
            animal.value = "Frog";
          } else {
            animal.value = "Salamander";
          }
        }
      }
    } else {
      if (await doChili("On land, are you a mammal?")) {
        if (await doChili("Are you commonly kept as a pet?")) {
          if (await doChili("Are you smaller than a house cat?")) {
            animal.value = "Hamster";
          } else {
            animal.value = "Dog";
          }
        } else {
          if (await doChili("Are you a big cat?")) {
            animal.value = "Lion";
          } else {
            animal.value = "Elephant";
          }
        }
      } else {
        if (await doChili("Do you have feathers?")) {
          if (await doChili("Can you fly?")) {
            animal.value = "Eagle";
          } else {
            animal.value = "Ostrich";
          }
        } else {
          if (await doChili("Do you have scales?")) {
            animal.value = "Snake";
          } else {
            animal.value = "Butterfly";
          }
        }
      }
    }
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
        <v-card title="Animal" :text="resultText"></v-card>
        <div class="d-flex justify-center mt-3">
          <v-btn color="purple" @click="doit" size="x-large">JUST DO IT</v-btn>
        </div>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped>
</style>
