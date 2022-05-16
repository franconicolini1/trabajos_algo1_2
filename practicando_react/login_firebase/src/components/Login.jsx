import React, { useState } from 'react'
import { useHistory } from 'react-router-dom'
import { auth } from '../firebaseConfig'

const MIN_PASS = 6

const Login = () => {
    const [email, setEmail] = useState('')
    const [pass, setPass] = useState('')
    const [msgError, setMsgError] = useState('')
    const history = useHistory()

    const registerUser = (e) => {
        setMsgError('')
        if (pass.length < MIN_PASS) return setMsgError('La contraseña debe tener 6 caracteres o mas')

        auth.createUserWithEmailAndPassword(email, pass)
        .then(() => {
            history.push('/')
        })
        .catch(() => {
            setMsgError('Email ya existente')
        })
    }

    const loginUser = () => {
        if (!email.trim() || !pass.trim()) return setMsgError('Ambos campos deben estar llenos')
        auth.signInWithEmailAndPassword(email, pass)
        .then(history.push('/'))
        .catch(() => {
            setMsgError('Email o password incorrectos')
        })
    }

    return (
        <div className='row mt-5'>
            <div className="col"></div>
            <div className="col">
                <form className='form-group'>
                    <input
                        onChange={(e) => setEmail(e.target.value)}
                        className='form-control'
                        placeholder='Introduzca su email'
                        type='email'
                        value={email ? email : ''}
                    />
                    <input
                        onChange={e => setPass(e.target.value)}
                        className='form-control mt-4'
                        placeholder='Introduzca su contraseña'
                        type='password'
                        value={pass ? pass : ''}
                    />
                    <input
                        className='btn btn-dark btn-block mt-5 w-100'
                        value='Registrar Usuario'
                        type='button'
                        onClick={e => registerUser(e)}
                    />
                </form>
                <button 
                    className='btn btn-success btn-block mt-3 w-100'
                    onClick={loginUser}
                >
                    Iniciar sesión
                </button>
                {
                    msgError ?
                    <p className='text-danger mt-3'>
                        {msgError}
                    </p>
                    :
                    <span></span>
                }
            </div>
            <div className="col"></div>
        </div>
    )
}

export default Login