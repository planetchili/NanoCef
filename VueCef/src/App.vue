<script setup lang="ts">
import { ref, computed } from 'vue'
interface Item {
  name: string;
  price: number;
}
const inventory: Item[] = [
  { name: 'Pepe\'s Existential Dread Poster', price: 14.00 },
  { name: 'Rickroll Remixes Vol. 420', price: 12.25 },
  { name: 'No Nut November Nutella', price: 6.50 },
  { name: 'Zoom Call Pajama Pants', price: 18.75 },
  { name: 'NPC Brainiac Gaming Chair', price: 149.00 },
  { name: 'Tide Pod Cereal Crunch', price: 4.25 },
  { name: 'Discord Mod Tears Spray', price: 8.50 },
  { name: 'HR\'s Quiet Firing Manual', price: 7.75 },
  { name: 'Twitch Streamer Rage Quit Button', price: 19.00 },
  { name: 'Dumpster Fire Candle Set', price: 29.25 },
  { name: 'Elon’s Cryo-Bricked Bitcoin Miner', price: 49.50 },
  { name: 'Musk’s Mars Colony Bond Scam', price: 14.75 },
  { name: 'Nigerian Prince Scam Starter Kit', price: 9.00 },
  { name: '420 Blaze It Cufflinks', price: 24.25 },
  { name: 'Karens of Twitter Anti-Block Spray', price: 7.50 },
  { name: 'Flat Earth Society Globe Eraser', price: 5.75 },
  { name: 'Crying Elon Meme Tissue Pack', price: 3.00 },
  { name: 'Area 51 Alien Adoption Papers', price: 12.25 },
  { name: 'Guinea Pig Therapist Hotline Subscription', price: 4.50 },
  { name: 'Dumpster Fire Rodeo Clown Costume', price: 49.75 },
]
interface Entry {
  item: Item;
  quantity: number;
}
const entries = ref<Entry[]>([])
function addItem() {
  entries.value.push({item: inventory[0], quantity: 1})
}
function removeItem(i: number) {
  entries.value.splice(i, 1)
}
const grandTotal = computed(() =>
  entries.value.reduce((sum, entry) => sum + entry.item.price * entry.quantity, 0)
)
const mb = ref('null')
function doit() {
  interface ChilApi {
    doChili(
      text: string,
      accept: (result: boolean) => void,
      reject: (msg: string) => void,
    ): void;
  }
  const chilApi = window as unknown as ChilApi;
  chilApi.doChili("ayyyyyy lmao",
    btn => { mb.value = btn ? 'YES' : 'NO' },
    msg => mb.value = msg
  )
}
</script>

<template>
  <v-app>
    <v-main>
      <v-container width="1024">
        <h2 class="mb-2 ml-4">My Shooping Cart</h2>
        <v-card class="mb-3 pa-3 pt-5">
          <v-row v-for="(entry, i) in entries" align="center">
            <v-col cols="1">
              <v-btn icon="mdi-trash-can" size="small" variant="text"
                color="red" @click="removeItem(i)"
              ></v-btn>
            </v-col>
            <v-col cols="7">
              <v-autocomplete
                color="primary"
                variant="outlined"
                density="compact"
                hide-details
                :items="inventory"
                item-title="name"
                v-model="entry.item"
                return-object
              ></v-autocomplete>
            </v-col>
            <v-col cols="2">
              <v-number-input
                color="primary"
                variant="outlined"
                density="compact"
                hide-details
                control-variant="stacked"
                v-model="entry.quantity"
                :min="1"
              ></v-number-input>
            </v-col>
            <v-col cols="2" class="d-flex justify-end">
              <p class="price">${{ (entry.item.price * entry.quantity).toFixed(2) }}</p>
            </v-col>
          </v-row>
          <v-row align="center">
            <v-col cols="10" class="d-flex justify-end">
              <p class="price" style="padding-right: 0">Grand Total:</p>
            </v-col>
            <v-col cols="2" class="d-flex justify-end">
              <p class="price">${{ grandTotal.toFixed(2) }}</p>
            </v-col>
          </v-row>
        </v-card>
        <div class="d-flex justify-end">
          <v-btn icon="mdi-plus" color="purple" @click="addItem"></v-btn>
        </div>
        <div class="d-flex justify-end">
          <v-btn color="green" @click="doit">AYY</v-btn>
          <p class="price">{{ mb }}</p>
        </div>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped>
.price {
  font-size: 20px;
  font-weight: bold;
  padding-right: 20px;
}
</style>
