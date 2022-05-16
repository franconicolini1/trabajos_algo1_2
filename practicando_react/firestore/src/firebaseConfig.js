import firebase from 'firebase/compat/app'
import 'firebase/compat/firestore'

const firebaseConfig = {
	apiKey: "AIzaSyCoXN1R5nPcfKp-Mrcmh3KYm8kOYbSuEIc",
	authDomain: "firestore-69abb.firebaseapp.com",
	projectId: "firestore-69abb",
	storageBucket: "firestore-69abb.appspot.com",
	messagingSenderId: "483560200198",
	appId: "1:483560200198:web:c955b3535e1932142ecb87",
	measurementId: "G-KJ6NWXXGDN"
}

const fire = firebase.initializeApp(firebaseConfig)
const db = fire.firestore()

export { db }