import firebase from 'firebase/compat/app'
import 'firebase/compat/auth'

const firebaseConfig = {
    apiKey: "AIzaSyDabHEk8dREH_G-5G93PriDOXxD0okZj3g",
    authDomain: "practicando-react.firebaseapp.com",
    projectId: "practicando-react",
    storageBucket: "practicando-react.appspot.com",
    messagingSenderId: "421355405755",
    appId: "1:421355405755:web:bf15a4a767d098622e449e",
    measurementId: "G-XVX85L5EZ8"
}

const fire = firebase.initializeApp(firebaseConfig)
const auth = fire.auth()

export { auth }